/*
 * General function form, for defining valid moves
 * By Danny Reilman <reilman@umich.edu>
 */
class Function {
public:
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
