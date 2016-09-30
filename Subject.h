/*
 * Class to handle generic asexually reproducing subjects.
 * Classes that inherit Subject should:
 * - Have a mutate function which will slightly change the aspects of the subject 
 * - Have some sort of external values which an evaluator can use to determine fitness
 * By Danny Reilman <reilman@umich.edu>
 */
class Subject
{
public:
	/*
	 * Method to change internal values
	 */
	virtual void Mutate() = 0;

	/*
	 * Method to clone the Subject
	 */
	virtual Subject* Clone() = 0;
};
