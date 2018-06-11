#include "matrix.hpp"

matrix_t::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

matrix_t::matrix_t( matrix_t const & other )
{       
	rows_ = other.rows();
	collumns_ = other.collumns();
	elements_ = new int *[rows_];
	for (unsigned int i = 0; i < rows_; ++i) {
		elements_[i] = new int[collumns_];
		for (unsigned int j = 0; j < collumns_; ++j) {
			elements_[i][j] = other.elements_[i][j];
		}
	}
}

matrix_t & matrix_t::operator =( matrix_t const & other )
{
	if (this != &other) {
		rows_ = other.rows();
		collumns_ = other.collumns();
		
		for (int i = 0; i < rows_; i++)
			delete[] elements_[i];
		
		delete[] elements_;
		
		elements_ = new int *[rows_];
		for (int i = 0; i < rows_; ++i) {
			elements_[i] = new int[collumns_];
			
		for (int j = 0; j < collumns_; ++j) {
			elements_[i][j] = other.elements_[i][j];
			}
		}
	}
	return *this;
}

matrix_t::~matrix_t()
{
	for (unsigned int i = 0; i < rows_; i++) {
			delete[] elements_[i];
		}
		delete[] elements_;
}

std::size_t matrix_t::rows() const
{
    return rows_;
}

std::size_t matrix_t::collumns() const
{
    return collumns_;
}

matrix_t matrix_t::operator +( matrix_t const & other ) const
{
	matrix_t result;
	result.rows_ = rows_;
	result.collumns_ = collumns_;
		if ((rows_ == other.rows_ && collumns_ == other.collumns_)) {
			result.elements_ = new int* [rows_];
			for (unsigned int i = 0; i < rows_; ++i) {
				result.elements_[i] = new int[collumns_];
				for (unsigned int j = 0; j < collumns_; ++j) {
					result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
				}
			}
		}
	else {
			std::cout << "An error has occured while reading input data.\n";
			exit(0);
		}
	return result;
}

matrix_t matrix_t::operator -( matrix_t const & other ) const
{
	matrix_t result;
	result.rows_ = rows_;
	result.collumns_ = collumns_;
		if ((rows_ == other.rows_ && collumns_ == other.collumns_)) {
			result.elements_ = new int *[rows_];
			for (unsigned int i = 0; i < rows_; ++i) {
				result.elements_[i] = new int[collumns_];
				for (unsigned int j = 0; j < collumns_; ++j) {
					result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
				}
			}
		}
	else {
			std::cout << "An error has occured while reading input data.\n";
			exit(0);
	}
	return result;
}

matrix_t matrix_t::operator *( matrix_t const & other ) const
{
	if (collumns_ == other.rows_) {
			matrix_t result;
		        result.rows_ = rows_;
	                result.collumns_ = collumns_;
			result.elements_ = new int *[rows_];
			for (unsigned int i = 0; i < rows_; ++i) {
				result.elements_[i] = new int[collumns_];
				for (unsigned int j = 0; j < other.collumns_; ++j) {
					result.elements_[i][j] = 0;
					for (int k = 0; k < collumns_; k++)
						result.elements_[i][j] += (elements_[i][k] * other.elements_[k][j]);
				}
			}
			return result;
		}
		else {
			std::cout << "An error has occured while reading input data.\n";
			exit(0);
		}
}

matrix_t & matrix_t::operator -=( matrix_t const & other )
{
	*this = *this - other;
	return *this;
}

matrix_t & matrix_t::operator +=( matrix_t const & other )
{
	*this = *this + other;
	return *this;
}

matrix_t & matrix_t::operator *=( matrix_t const & other )
{
   *this = *this * other;
    return *this;
}

std::istream & matrix_t::read( std::istream & stream )
{
    std::size_t rows;
    std::size_t collumns;
    char symbol;
    
    bool success = true;
    if( stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns ) {
    	int ** elements = new int *[ rows ];
        for( std::size_t i = 0; success && i < rows; ++i ) {
            elements[ i ] = new int[ collumns ];
            for( std::size_t j = 0; j < collumns; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }
        
        if( success ) {
            for( std::size_t i = 0; i < rows_; ++i ) {
                delete [] elements_[ i ];
            }
            delete [] elements_;
            
            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else {
            for( std::size_t i = 0; i < rows; ++i ) {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else stream.setstate( std::ios_base::failbit );
	
	return stream;
}

std::ostream & matrix_t::write( std::ostream & stream ) const
{
    stream << rows_ << ", " << collumns_;
    for( std::size_t i = 0; i < rows_; ++i ) {
        stream << '\n';
        for( std::size_t j = 0; j < collumns_; ++j ) {
            stream << elements_[ i ][ j ];
	    if (rows_ == 1 && j != 1) stream << ' ';
            if( j != rows_ - 1 ) {
               stream << ' ';
            }
        }
    }
    
	return stream;
}
