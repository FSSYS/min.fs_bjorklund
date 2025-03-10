/*

An implementation of the Bjorklund algorithm in JavaScript

Inspired by the paper 'The Euclidean Algorithm Generates Traditional Musical Rhythms' 
by Godfried Toussaint

Original algorithm:

E. Bjorklund.

This implementation: David Braun

*/



inlets = 1;
outlets = 1;

function anything(pulses, steps) 
{bjorklund(pulses, steps);}


function bjorklund(pulses, steps) 
{
	if (steps >= pulses && steps > 1)
	{
		var pauses = steps - pulses;
		var rythm = new Array();
		var colSizes = new Array();
		
		//build arrays
		for (var i = 0; i < pulses; i++)
		{
			rythm.push(1);
			colSizes.push(1);			
		}	
		for (var i = 0; i < pauses; i++)
		{
			rythm.push(0);
			colSizes.push(1);
		}
		
		//actual algorithm
		while ( !((pauses==1 && pulses==1) || (pauses==0 || pulses==0)) )
		{
			var counter = 0;
			
			if (pauses>pulses)
			{
				counter = pulses;
				pauses -= pulses;
			}
			else
			{
				counter = pauses;
				pulses -= pauses;
			}
			
			var writePosition = 0;
			
			var level = colSizes[colSizes.length - 1];
			
			for (var i = 0; i < counter; i++)
			{
				writePosition += colSizes[i];
				
				var readPosition = rythm.length - level;				
				var elementsToMove = rythm.splice(readPosition, level);
				
				for (var j = 0; j < elementsToMove.length; j++)				
				{
					rythm.splice(writePosition, 0, elementsToMove[j]);
					writePosition ++;
				}					
				colSizes[i] += level;
				colSizes.pop();											
			}			
		}
		outlet(0, rythm);				
	}
}
