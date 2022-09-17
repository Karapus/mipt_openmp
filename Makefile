CXXFLAGS += -O2 -Wall -Wextra --std=c++20 -fopenmp -fopenmp-version=52

balance: run_balance_static run_balance_dynamic run_balance_guided run_balance_default

run_balance_static: balance_static_1.out balance_static_4.out
run_balance_dynamic: balance_dynamic_1.out balance_dynamic_4.out
run_balance_guided: balance_guided_1.out balance_guided_4.out
run_balance_default: balance_default.out

balance_default.out: extra/balance.cc
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$@ | sort > $(addsuffix .log,$(basename $@))

balance_get_shedule = $(word 1,$(subst _, ,$(1)))
balance_get_chunk = $(word 2,$(subst _, ,$(1)))

balance_%.out: extra/balance.cc
	$(CXX) -DSCHEDULE='schedule($(call balance_get_shedule,$*), $(call balance_get_chunk,$*))' $(CXXFLAGS) $^ -o $@
	./$@ | sort > $(addsuffix .log,$(basename $@))
