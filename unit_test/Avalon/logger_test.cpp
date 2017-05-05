#include <gtest/gtest.h>
#define OPEN_LOG_PORT warn,err,dev
#include <Avalon/util/logger.hpp>
#include <sstream>
TEST(logger, basic_test)
{
    EXPECT_EQ(&avalon::util::msg .get_ostream()   , &avalon::util::logger::nout   );
    EXPECT_EQ(&avalon::util::warn.get_ostream()   , &std::cout                    );
    EXPECT_EQ(&avalon::util::err .get_ostream()   , &std::cerr                    );
    EXPECT_EQ(&avalon::util::dbg .get_ostream()   , &avalon::util::logger::nout   );
    EXPECT_EQ(&avalon::util::dev .get_ostream()   , &std::cerr                    );
}
TEST(logger, ostream_test)
{
    std::stringstream ss; 
    avalon::util::dev.set_ostream(&ss);
    avalon::util::dev << "test message" << std::endl;
    std::stringstream ss2;
    ss2 <<  "[" << std::setw(6) << "DEV" << "] : " << "test message" << std::endl;
    EXPECT_EQ(ss.str(), ss2.str());
}
TEST(logger, wostream_test)
{
    auto ws = avalon::util::logger::make_adapter(
          avalon::make_const_string(L"WTEST")
        , std::wcout
    );
    std::wcout << L"\x5355\x5143\x683c" << std::endl;;
    // ws << "輸出字串" << std::endl;
}