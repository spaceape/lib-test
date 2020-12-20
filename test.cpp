/**
    Copyright (c) 2020, wicked systems

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
    THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
    OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#include "base.h"
#include <limits>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

constexpr char      s_tag_blank[] ="    ";
constexpr char      s_tag_passed[] ="\x1b[0m\x1b[1;32mPASS\x1b[0m";
constexpr char      s_tag_failed[] ="\x1b[0m\x1b[1;31mFAIL\x1b[0m";
constexpr size_t    s_summary_length_max = 1024;
// constexpr size_t s_output_length_max = 3072;

static  test::base* s_harness;
static  test::base* s_head;
static  test::base* s_tail;
static  char        s_summary[s_summary_length_max];

namespace test {

      base::base(const char* name) noexcept
{
      m_name = name;
      m_description = nullptr;
      if(s_tail) {
          if(s_tail->m_index == std::numeric_limits<unsigned int>::max()) {
              abort();
          }
          m_index = s_tail->m_index + 1;
      } else
          m_index = 1;
      m_prev = s_tail;
      m_next = nullptr;
      if(s_tail) {
          s_tail->m_next = this;
      } else
          s_head = this;
      s_tail = this;

}

      base::~base()
{
      if(m_prev) {
          m_prev->m_next = m_next;
      } else
          s_head = m_next;
      if(m_next) {
          m_next->m_prev = m_prev;
      } else
          s_tail = m_prev;
}

base* base::get_harness() noexcept
{
      return s_harness;
}

void  base::set_harness(base* object) noexcept
{
      s_harness = object;
}

unsigned int base::get_test_count() noexcept
{
      if(s_tail) {
          return s_tail->m_index;
      } else
          return 0;
}

bool  base::pass() noexcept
{
      return true;
}

bool  base::fail() noexcept
{
      return false;
}

void  base::print_test_header() const noexcept
{
      fprintf(stdout, "[ %s ] %d/%d\r", s_tag_blank, get_index(), get_test_count());
}

void  base::print_test_result(bool result) const noexcept
{
      const char* tag;
      if(result) {
          tag = s_tag_passed;
      } else
          tag = s_tag_failed;
      fprintf(stdout, "[ %s ] %d/%d", tag, get_index(), get_test_count());
      if(has_description()) {
          fprintf(stdout, ": %s", get_description());
      }
      fprintf(stdout, "\n");
}

void  base::print_test_summary(bool, const char* summary) const noexcept
{
      if(summary) {
          if(summary[0]) {
              fprintf(stdout, "%s\n", summary);
          }
      }
}

unsigned int  base::get_index() const noexcept
{
      return m_index;
}

const char* base::get_name() const noexcept
{
      return m_name;
}

void  base::set_name(const char* name) noexcept
{
      m_name = name;
}

bool  base::has_description() const noexcept
{
      return m_description && m_description[0];
}

const char* base::get_description() const noexcept
{
      return m_description;
}

void  base::set_description(const char* description) noexcept
{
      m_description = description;
}

base* base::get_prev() const noexcept
{
      return m_prev;
}

base* base::get_next() const noexcept
{
      return m_next;
}

bool  base::operator()() noexcept
{
      return execute();
}

      base::operator int() noexcept
{
      if(execute()) {
          return 0;
      } else
          return 127;
}

      base::operator bool() noexcept
{
      return execute();
}

/* set_name
*/
void  set_name(const char* name) noexcept
{
      if(s_harness) {
          s_harness->set_name(name);
      }
}

/* set_description
*/
void  set_description(const char* description) noexcept
{
      if(s_harness) {
          s_harness->set_description(description);
      }
}

const char* set_summary(const char* fmt, ...) noexcept
{
      va_list ap;
      va_start(ap, fmt);
      if(fmt) {
          vsnprintf(s_summary, s_summary_length_max, fmt, ap);
      }
      va_end(ap);
      return s_summary;
}

const char* get_summary() noexcept
{
      return s_summary;
}

int   run_all() noexcept
{
      int   l_result = 0;
      auto  l_iter   = s_head;
      while(l_iter) {
          if(l_iter->execute() == false) {
              l_result |= 127;
          }
          l_iter = l_iter->get_next();
      }
      return l_result;
}

int   run_scenario(base*) noexcept
{
      return 255;
}

/*namespace test*/ }
