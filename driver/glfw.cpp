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
#include "glfw.h"
#include <GL/gl.h>
#include <test.h>

      GLFW::GLFW(const GLFW& copy) noexcept:
      m_call(copy.m_call),
      m_window_sx(copy.m_window_sx),
      m_window_sy(copy.m_window_sy)
{
}

      GLFW::GLFW(GLFW&& copy) noexcept:
      m_call(std::move(copy.m_call)),
      m_window_sx(copy.m_window_sx),
      m_window_sy(copy.m_window_sy)
{
}

      GLFW::~GLFW()
{
}

void  GLFW::resize(GLFWwindow* window, int sx, int sy) noexcept
{
      glViewport(0, 0, sx, sy);
}

bool  GLFW::fail(GLFWwindow*) noexcept
{
      return false;
}

bool  GLFW::execute() const noexcept
{
      GLFWwindow* window;
      bool        result = false;
      if(glfwInit() == GLFW_TRUE) {
          glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
          glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
          glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
          window = glfwCreateWindow(m_window_sx, m_window_sy, "Ohai", nullptr, nullptr);
          if(window) {
              glfwMakeContextCurrent(window);
              glViewport(0, 0, m_window_sx, m_window_sy);
              glfwSetFramebufferSizeCallback(window, resize);
              auto tm0 = std::chrono::system_clock::now();
              result = m_call(window);
              auto tm1 = std::chrono::system_clock::now();
              auto dt  = std::chrono::duration<double>(tm1 - tm0);
              if(result) {
                  if(dt.count() < 1.0) {
                      test::set_summary("(i) Total execution time: %.3fms", dt.count() * 1000);
                  } else
                      test::set_summary("(i) Total execution time: %.3fs", dt.count());
              } else
                  test::set_summary(nullptr);
          }
          glfwTerminate();
      }
      return result;
}
