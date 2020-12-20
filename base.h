#ifndef test_base_h
#define test_base_h
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
#include <stdlib.h>

namespace test {

class base
{
  const char*   m_name;
  const char*   m_description;
  unsigned int  m_index;
  base*         m_prev;
  base*         m_next;

  protected:
          void  print_test_header() const noexcept;
          void  print_test_result(bool) const noexcept;
          void  print_test_summary(bool, const char*) const noexcept;
  static  base* get_harness() noexcept;
  static  void  set_harness(base*) noexcept;
  static  unsigned int  get_test_count() noexcept;

  public:
  static  bool  pass() noexcept;
  static  bool  fail() noexcept;

  public:
          base(const char*) noexcept;
          base(const base&) noexcept = delete;
          base(base&&) noexcept = delete;
  virtual ~base();
          unsigned int  get_index() const noexcept;
          const char*   get_name() const noexcept;
          void          set_name(const char*) noexcept;
          bool          has_description() const noexcept;
          const char*   get_description() const noexcept;
          void          set_description(const char*) noexcept;
          base*         get_prev() const noexcept;
          base*         get_next() const noexcept;
  virtual bool          execute() noexcept = 0;
          bool          operator()() noexcept;
          operator      int() noexcept;
          operator      bool() noexcept;
          base&         operator=(const base&) noexcept = delete;
          base&         operator=(base&&) noexcept = delete;
};


void        set_name(const char* name) noexcept;
void        set_info(const char* description) noexcept;
const char* set_summary(const char* fmt, ...) noexcept;
const char* get_summary() noexcept;

/*namespace test*/ }
#endif
