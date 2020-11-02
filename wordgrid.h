// Provided by Professor Campbell
#include <iostream>

using namespace std;

// class wordgrid provides an infrastructure for square (DxD)
// grids of letters. Each slot is referenced with a row number r,
// 0 <= r < D and a column number c, 0 <= c < D.

class wordgrid {
public:
//-wordgrid(size_t d, string data)----------------------------------------
wordgrid(size_t d, string data);
// PRE: second parameter is an long string of lowercase letters,
// which is the data for all the rows of the d x d grid.
// (data.length() == d * d)
// POST: initialize the instance with the data.
//------------------------------------------------------------------------
//-size_t size() const----------------------------------------------------
size_t size() const;
// RETURN: The dimension of the grid (length of one side)
//------------------------------------------------------------------------
//-char get(size_t r, size_t c) const ------------------------------------
char get(size_t r, size_t c) const;
// PRE: r < size() and c < size()
// RETURN: the character at position (r,c)
//------------------------------------------------------------------------
//-void set(size_t r, size_t c, char v)-----------------------------------
void set(size_t r, size_t c, char v);
// PRE: same as get
// POST: the character at position (r,c) is now v
//------------------------------------------------------------------------
//-void output(ostream & ostr) const--------------------------------------
void output(ostream & ostr) const;
// POST: The contents of the grid are produced on the
// output stream in rows terminated by newlines.
//------------------------------------------------------------------------
private:
wordgrid(const wordgrid &); // disable copy constructor
char * _data;
size_t _dim;
size_t _getLoc(size_t r, size_t c) const;
};
// -ostream & operator<<(ostream & ostr, const wordgrid & wg)---------------
// support the stream output operator so that
// statements like 'cout << wg;' works when
// wg is a wordgrid.
ostream & operator<<(ostream & ostr, const wordgrid & wg);
