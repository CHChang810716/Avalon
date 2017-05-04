#include <gtest/gtest.h>
#define OPEN_LOG_PORT warn,err,dev
#include <Avalon/util/logger.hpp>
TEST(logger, basic_test)
{
    EXPECT_EQ(&avalon::util::msg    , &avalon::util::logger::nout   );
    EXPECT_EQ(&avalon::util::warn   , &std::cout                    );
    EXPECT_EQ(&avalon::util::err    , &std::cerr                    );
    EXPECT_EQ(&avalon::util::dbg    , &avalon::util::logger::nout   );
    EXPECT_EQ(&avalon::util::dev    , &std::cerr                    );
}