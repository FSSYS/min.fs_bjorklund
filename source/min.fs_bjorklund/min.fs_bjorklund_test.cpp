/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min_unittest.h"     // required unit test header
#include "min.fs_bjorklund.cpp"    // need the source of our object so that we can access it

// Unit tests are written using the Catch framework as described at
// https://github.com/philsquared/Catch/blob/master/docs/tutorial.md

SCENARIO("object produces correct output") {
    ext_main(nullptr);    // every unit test must call ext_main() once to configure the class

    using std::cout;
    using std::endl;

    GIVEN("An instance of our object") {

        test_wrapper<fs_bjorklund> an_instance;
        fs_bjorklund&              my_object = an_instance;
        atoms input{ 3, 8 , 0};
        atoms testres{ 1, 0, 0,1,0,0,1,0 };
        my_object.list(input);
        auto& output = *c74::max::object_getoutput(my_object, 0);
        REQUIRE((output.size() == 8));
        //REQUIRE((output[0] == input.size()));
        for (auto i = 0; i < output.size(); ++i) {
            REQUIRE((output[0][i] == testres[i]));
        }
    }
}
