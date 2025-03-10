/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
#include <vector>

using namespace c74::min;


class fs_bjorklund : public object<fs_bjorklund> {
public:
    MIN_DESCRIPTION	{ "Euclidean rhythm generator" };
    MIN_TAGS		{ "time" };
    MIN_AUTHOR		{ "FSSYS" };
    MIN_RELATED		{ "min.beat.pattern, link.beat, metro, tempo, drunk" };

    inlet<>  input			{ this, "(list) beats/steps or beats/steps/phase" };
    outlet<> output		{ this, "(list) rhythm as string of 1 and 0" };

    static atoms bbjorklund(const int pulse,const int step) {
        const int pauses = step - pulse;
        int remainder = pauses % pulse;
        int per_pulse = pauses / pulse;
        int noskip = (remainder == 0) ? 0 : pulse / remainder;
        int skipXTime = (noskip == 0) ? 0 : (pulse - remainder) / noskip;
        atoms rhythm;
        rhythm.reserve(step);
        int count = 0;
        int skipper = 0;
        for (int i = 1; i <= step; i++) {
            if (count == 0) {
                rhythm.push_back(1);
                count = per_pulse;
                if (remainder > 0 && skipper == 0) {
                    count++;
                    remainder--;
                    skipper = (skipXTime > 0) ? noskip : 0;
                    skipXTime--;
                }
                else {
                    skipper--;
                }
            }
            else {
                rhythm.push_back(0);
                count--;
            }
        }
        return rhythm;
    }
    void rotate(int phase, atoms* list) {
        std::rotate(list->begin(), list->end() - phase, list->end());
        return;
    }

   message<> list{
    this, "list", "create rhythm with beats/steps/(phase)",
    MIN_FUNCTION
    {
        if (args.size() == 3){
            if (args[0] == 0) {
                output.send(atoms(args[1], 0));
            }
            else if (args[0] == args[1]) {
                output.send(atoms(args[1], 1));
            }
            else {
                auto res = bbjorklund(args[0], args[1]);
                rotate((int)args[2] % (int)args[1], &res);
                output.send(res);
            }
        }
        
        else if (args.size() == 2) {
            if (args[0] == 0) {
                output.send(atoms(args[1], 0));
            }
            else if (args[0] == args[1]) {
                output.send(atoms(args[1], 1));
            }
            else {
                output.send(bbjorklund(args[0], args[1]));
            }
        }

        return{};
    }
};

};


MIN_EXTERNAL(fs_bjorklund);
