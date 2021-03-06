// Copyright (C) 2013    Romain Francois
// Copyright (C) 2013    Rice University
//
// This file is part of dplyr.
//
// dplyr is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// dplyr is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with dplyr.  If not, see <http://www.gnu.org/licenses/>.

#ifndef dplyr_DataFrameJoinVisitors_H
#define dplyr_DataFrameJoinVisitors_H

namespace dplyr{
    
    class DataFrameJoinVisitors : 
        public VisitorSetEqual<DataFrameJoinVisitors>, 
        public VisitorSetHash<DataFrameJoinVisitors>
    {
    public:
        typedef JoinVisitor visitor_type ;
        
        DataFrameJoinVisitors(const Rcpp::DataFrame& left_, const Rcpp::DataFrame& right_, Rcpp::CharacterVector names_) : 
            left(left_), right(right_), visitor_names(names_), nvisitors(names_.size()), visitors(nvisitors)
        {    
            std::string name ;
            for( int i=0; i<nvisitors; i++){
                name = names_[i] ;
                visitors[i] = join_visitor( left[name], right[name]) ;
            }
        }
        
        ~DataFrameJoinVisitors(){
            delete_all(visitors);    
        }
        
        inline JoinVisitor* get(int k) const { return visitors[k] ; }
        inline int size() const{ return nvisitors ; } 
        
        template <typename Container>
        inline DataFrame subset( const Container& index, const CharacterVector& classes ){
            int nrows = index.size() ;
            Rcpp::List out(nvisitors);
            for( int k=0; k<nvisitors; k++){
               out[k] = get(k)->subset(index) ;    
            }
            out.attr( "class" ) = classes ;
            set_rownames(out, nrows) ;
            out.names() = visitor_names ;
            SEXP vars = left.attr( "vars" ) ;
            if( !Rf_isNull(vars) )
                out.attr( "vars" ) = vars ;
            return out.asSexp() ;
        }
        
    private:
        const DataFrame& left ;
        const DataFrame& right ;
        CharacterVector visitor_names ;
        int nvisitors ;
        std::vector<JoinVisitor*> visitors ;
        
    } ;
    
}

#endif

