#ifndef test_scenario_h
#define test_scenario_h
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

namespace test {

template<typename Dt>
class scenario: public test::base
{
  Dt  m_driver;

  public:
  template<typename Xt>
  inline  scenario(Xt&& target, const char* description = nullptr) noexcept:
          base(__PRETTY_FUNCTION__),
          m_driver(std::forward<Xt>(target)) {
          set_description(description);
  }

  template<typename Xt, typename... Args>
  inline  scenario(Xt&& target, Args&&... args) noexcept:
          base(__PRETTY_FUNCTION__),
          m_driver(std::forward<Xt>(target), std::forward<Args>(args)...) {
  }

  template<typename Xt, typename Ft>
  inline  scenario(Xt&& object, Ft&& function, const char* description = nullptr) noexcept:
          base(__PRETTY_FUNCTION__),
          m_driver(std::forward<Xt>(object), std::forward<Ft>(function)) {
          set_description(description);
  }

  inline  ~scenario() {
  }

  /**/    bool  execute() noexcept override {
          bool  result = false;
          if(base::get_harness() == nullptr) {
              base::set_harness(this);
              base::print_test_header();
              result = m_driver.execute();
              base::print_test_result(result);
              base::print_test_summary(result, get_summary());
              base::set_harness(nullptr);
          }
          return result;
  }
};

/*namespace test*/ }
#endif
