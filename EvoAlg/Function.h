/*
 * General function form, for defining valid moves
*/
class Function {
	/*
	 * Returns the number of arguments that should be sent into evaluate
	 */
	int numArgs();

	/*
	 * Requires: arguments.length == numArgs();
	 *  Returns the function evaluated over the arguments.
	 */
	int eval(int[]);
};
