// generate a börklund sequence, code from here: https://bitbucket.org/sjcastroe/bjorklunds-algorithm/src/master/Bjorklund's%20Algorithm/bjorklund.cpp  
// 11olsen.de

function bang()//test
{
	;
	
}	

function anything(a, b)
{
	outlet(0, bjorklund2(a, b) );
}


function bjorklund2(beats, steps)
{
	//We can only have as many beats as we have steps (0 <= beats <= steps)
	if (beats > steps)
		beats = steps;

	//Each iteration is a process of pairing strings X and Y and the remainder from the pairings
	//X will hold the "dominant" pair (the pair that there are more of)
	var x = "1";
	var x_amount = beats;

	var y = "0";
	var y_amount = steps - beats;

	do
	{
		//Placeholder variables
		var x_temp = x_amount;
		var y_temp = y_amount;
		var y_copy = y; // string

		//Check which is the dominant pair 
		if (x_temp >= y_temp)
		{
			//Set the new number of pairs for X and Y
			x_amount = y_temp;
			y_amount = x_temp - y_temp;

			//The previous dominant pair becomes the new non dominant pair
			y = x;
		}
		else
		{
			x_amount = x_temp;
			y_amount = y_temp - x_temp;
		}

		//Create the new dominant pair by combining the previous pairs
		x = x + y_copy;
	} while (x_amount > 1 && y_amount > 1);//iterate as long as the non dominant pair can be paired (if there is 1 Y left, all we can do is pair it with however many Xs are left, so we're done)

	//By this point, we have strings X and Y formed through a series of pairings of the initial strings "1" and "0"
	//X is the final dominant pair and Y is the second to last dominant pair
	var rhythm = "";
	for ( i = 1; i <= x_amount; i++) 
		rhythm += x;
	for ( i = 1; i <= y_amount; i++)
		rhythm += y;
		
	return rhythm.split('').map(function(item) 
	{
    	return parseInt(item, 10);
	});
}




function rotateArray(A, K) {
    if (!A.length) return A;
    var index = -1;
    while (++index < K) {
        A.unshift(A.pop());
    }
    return A;
}