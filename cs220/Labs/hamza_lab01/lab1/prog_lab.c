/* Implementation of the fact function goes here. */
int fact(int n){
	int result;
	int count;
	result = 1;
	if (n <= 1) return result;

	else{
		count = n;
		
		while (count > 1){
			result *= count;
			count--;
		}
	return result;
	}
}
