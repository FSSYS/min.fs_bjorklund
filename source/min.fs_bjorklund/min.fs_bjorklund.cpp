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
    static atoms bbjorklund(const int pulse, const int step, const int phase) {
        auto res = bbjorklund(pulse, step);
        std::rotate(res.begin(), res.end() - modulo(phase, step), res.end());
        return res;
    }
    static unsigned modulo(int value, unsigned m) {
        int mod = value % (int)m;
        if (mod < 0) {
            mod += m;
        }
        return mod;
    }

   message<threadsafe::yes> list{
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
                lock lock{ m_mutex };
                auto res = bbjorklund(args[0], args[1], args[2]);
                lock.unlock();
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
                lock lock{ m_mutex };
                auto res = bbjorklund(args[0], args[1]);
                lock.unlock();
                output.send(res);
            }
        }

        return{};
    }
};
private:
    mutex m_mutex;
};


MIN_EXTERNAL(fs_bjorklund);


/*
class fs_nbjorklund : public object<fs_nbjorklund> {
public:
    MIN_DESCRIPTION{ "Nested Euclidean rhythm generator" };
    MIN_TAGS{ "time" };
    MIN_AUTHOR{ "FSSYS" };
    MIN_RELATED{ "min.beat.pattern, link.beat, metro, tempo, drunk" };

    inlet<>  input{ this, "(list) beats/steps or beats/steps/phase" };
    outlet<> output{ this, "(list) rhythm as string of 1 and 0" };

    static atoms bbjorklund(const int pulse, const int step) {
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
    static atoms bbjorklund(const int pulse, const int step, const int phase) {
        auto res = bbjorklund(pulse, step);
        std::rotate(res.begin(), res.end() - phase, res.end());
        return res;
    }

    static atoms nbjorklund(const int toppulse, const int topstep, const int topphase, const int bpulse, const int bstep, const int bphase) {
        auto top = bbjorklund(toppulse, topstep, topphase);

    }

    message<> list{
     this, "list", "create rhythm with beats/steps/(phase)",
     MIN_FUNCTION
     {
         if (args.size() == 3) {
             if (args[0] == 0) {
                 output.send(atoms(args[1], 0));
             }
             else if (args[0] == args[1]) {
                 output.send(atoms(args[1], 1));
             }
             else {
                 output.send(bbjorklund(args[0], args[1],args[2]));
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


MIN_EXTERNAL(fs_nbjorklund);

*/
