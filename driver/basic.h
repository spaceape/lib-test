#ifndef test_driver_basic_h
#define test_driver_basic_h
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
#include <base.h>
#include <functional>

class basic
{
  std::function<bool(void)> m_call;

  public:
          basic() noexcept;

  template<typename Xt>
  inline  basic(Xt&& target) noexcept {
      if constexpr (std::is_pointer<Xt>::value) {
          if constexpr (std::is_invocable<Xt>::value) {
              m_call = target;
          } else
              m_call = test::base::fail;
      } else
      if constexpr (std::is_invocable<Xt>::value) {
          m_call = [target](){ return target(); };
      } else
          m_call = test::base::fail;
  }

  template<typename Xt, typename Ft>
  inline  basic(Xt&& object, Ft&& method) noexcept {
      if constexpr (std::is_member_function_pointer<Ft>::value) {
          if constexpr (std::is_pointer<Xt>::value) {
              m_call = [object, method](){ return (object->*method)(); };
          } else
              m_call = [&object, method](){ return (object.*method)(); };
      } else
          m_call = test::base::fail;
  }

          basic(const basic&) noexcept;
          basic(basic&&) noexcept;
          ~basic();
          bool   execute() const noexcept;
          basic& operator=(const basic&) noexcept;
          basic& operator=(basic&&) noexcept;
};
#endif
