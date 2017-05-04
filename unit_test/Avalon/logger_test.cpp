#include <gtest/gtest.h>
#define OPEN_LOG_PORT warn,err,dev
#include <Avalon/util/logger.hpp>
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
    avalon::util::warn << "test message" << std::endl;
}