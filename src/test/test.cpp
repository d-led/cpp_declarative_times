#include <declarative_times.h>

#include <catch.hpp>
#include <algorithm>
#include <limits>

using namespace declarative_times;

struct declarative_times_should {
    using CountType = execute<>::CountType;

    CountType executed_times = 0;
    CountType last_seen_counter = std::numeric_limits<CountType>::max();
    CountType min_seen_counter = std::numeric_limits<CountType>::max();
    CountType max_seen_counter = 0;

    void increment() {
        executed_times++;
    }

    void tick(CountType value) {
        increment();
        min_seen_counter = std::min(min_seen_counter, value);
        max_seen_counter = std::max(max_seen_counter, value);
        last_seen_counter = value;
    }
};

TEST_CASE_METHOD(declarative_times_should, "not loop for 0-times") {
    0_times([this] { increment(); });
    CHECK(executed_times == 0);
}

TEST_CASE_METHOD(declarative_times_should, "loop for the specified amount of times") {
    42_times([this] { increment(); });
    CHECK(executed_times == 42);
}

TEST_CASE_METHOD(declarative_times_should, "work for non-constant counters too") {
    unsigned non_const_times = 21;
    non_const_times++;

    run(non_const_times)([this] { increment(); });
    CHECK(executed_times == non_const_times);
}

TEST_CASE_METHOD(declarative_times_should, "start from non-zero values too") {
    (2_times_with_index)
        .starting_from(2)
        ([this](CountType i) { tick(i); });

    CHECK(executed_times == 2);
    CHECK(min_seen_counter == 2);
    CHECK(max_seen_counter == 3);
}

TEST_CASE_METHOD(declarative_times_should, "start from non-zero values with custom step") {
    (3_times_with_index)
        .starting_from(2)
        .with_step(3)
        ([this](CountType i) { tick(i); });

    CHECK(executed_times == 3);
    CHECK(min_seen_counter == 2);
    CHECK(max_seen_counter == 8);
}

TEST_CASE_METHOD(declarative_times_should, "terminate on counter overflow and wrap it as expected") {
    (3_times_with_index)
        .starting_from(2)
        .with_step(std::numeric_limits<CountType>::max())
        ([this](CountType i) { tick(i); });

    CHECK(executed_times == 3);
    CHECK(min_seen_counter == 0);
    CHECK(last_seen_counter == 0);
    CHECK(max_seen_counter == 2);
}

TEST_CASE_METHOD(declarative_times_should, "be immutable") {
    SECTION("initial configuration") {
        auto three = 3_times_with_index;
        three([this](CountType i) { tick(i); });

        CHECK(executed_times == 3);
        CHECK(last_seen_counter == 2);

        SECTION("with respect to the starting index") {
            three.starting_from(3)([this](CountType i) { tick(i); });
            CHECK(executed_times == 6);
            CHECK(last_seen_counter == 5);

            three([this](CountType i) { tick(i); });
            CHECK(last_seen_counter == 2);
        }

        SECTION("with respect to the step size") {
            three
                .starting_from(3)
                .with_step(2)
                ([this](CountType i) { tick(i); });
            CHECK(last_seen_counter == 7);

            three([this](CountType i) { tick(i); });
            CHECK(last_seen_counter == 2);
        }
    }
}
