#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

struct __declspec(dllexport)  point {
  double x;
  double y;
};

namespace all_Body
{
	class __declspec(dllexport)  body {
	public:

		void print () const;
		double sum ();
		//______
		double x = 0;
		double y = 0;
	private:
		//______
		double step = 1;
	};
}