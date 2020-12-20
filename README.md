# lib-test
Small C++ test library

Usage example:

bool  test_31() noexcept
{
 ...
 return true;
}


      test::scenario<basic> t31(test_31, "[31] sys::sio empty get_char()");
      test::scenario<basic> t32(test_32, "[32] sys::sio empty read(0)");
      test::scenario<basic> t33(test_33, "[33] sys::sio empty read(256)");
      test::scenario<basic> t34(test_34, "[34] sys::sio empty read(256) with reserve()");
      test::scenario<basic> t35(test_35, "[35] sys::sio read(256) with load() of 11 characters");
      test::scenario<basic> t36(test_36, "[36] sys::sio read(256) with load() of 11 characters with buffer compare");

      test::scenario<basic> t41(test_41, "[41] sys::bio empty get_char()");
      test::scenario<basic> t42(test_42, "[42] sys::bio empty read(0)");
      test::scenario<basic> t43(test_43, "[43] sys::bio empty read(256)");
      test::scenario<basic> t44(test_44, "[44] sys::bio empty read(256) with reserve()");

      return test::run_all();
