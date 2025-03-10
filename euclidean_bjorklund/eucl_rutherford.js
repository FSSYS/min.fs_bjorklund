/*

An implementation of the Bjorklund algorithm in JavaScript

Inspired by the paper 'The Euclidean Algorithm Generates Traditional Musical Rhythms' 
by Godfried Toussaint

This is a port of the original algorithm by E. Bjorklund which I
found in the paper 'The Theory of Rep-Rate Pattern Generation in the SNS Timing Systems' by
E. Bjorklund.

Jack Rutherford

*/


function anything(pulses, steps) {
	
	steps = Math.round(steps);
	pulses = Math.round(pulses);	

	if(pulses > steps || pulses == 0 || steps == 0) {
		return new Array();
	}

	pattern = [];
	   counts = [];
	   remainders = [];
	   divisor = steps - pulses;
	remainders.push(pulses);
	level = 0;

	while(true) {
		counts.push(Math.floor(divisor / remainders[level]));
		remainders.push(divisor % remainders[level]);
		divisor = remainders[level]; 
	       level += 1;
		if (remainders[level] <= 1) {
			break;
		}
	}
	
	counts.push(divisor);

	var r = 0;
	var build = function(level) {
		r++;
		if (level > -1) {
			for (var i=0; i < counts[level]; i++) {
				build(level-1); 
			}	
			if (remainders[level] != 0) {
	        	build(level-2);
			}
		} else if (level == -1) {
	           pattern.push(0);	
		} else if (level == -2) {
           pattern.push(1);        
		} 
	};

/*

following code by cudnylon

*/

        build(level);
	pattern = pattern.reverse();
	
	if (pattern[0]==0)
    {
    var laststep = pattern.pop();
    pattern.unshift(laststep);

    	if (pattern[0]==0)
    	{
		var onestep = pattern.shift();
		pattern.push(onestep);
		var twostep = pattern.shift();
		pattern.push(twostep);
    	outlet(0, pattern);
    	}

		else
		{
		outlet(0, pattern);
		}
	}	
	
    else
    {
	outlet(0, pattern);
    }
}
