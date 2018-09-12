#include <iostream>
#include <stdio.h>
#include "boost/filesystem.hpp" 

using namespace boost::filesystem;

int main(int argc, char **argv) {
    
    path p(".");

    for (auto &entry : directory_iterator(p)) {
        std::cout << entry.path().string() << is_regular_file(entry.path()) << "\n";
        if (exists(p))    // does p actually exist?
            {
            if (is_regular_file(p))        // is p a regular file?   
            std::cout << p << " size is " << file_size(p) << '\n';

            else if (is_directory(p))      // is p a directory?
            std::cout << p << "is a directory\n";

            else
            std::cout << p << "exists, but is neither a regular file nor a directory\n";
            }
    else
        std::cout << p << "does not exist\n";
    }
    auto it = searcher(text.begin(),text.end());
    std::string texthtml = text;
    boost::container::flat_set< std::string > linkids;
    while(it != text.end())
    {

        it = std::next(it,8);

        auto end = std::find_if_not(it,text.end(),[](const char& c){return std::isdigit(c);});
        if(it != end)

            linkids.insert(std::string(it,end));

        it = searcher(end,text.end());

    }
    return 0;
}



// std::string replaceLinkIdsWithLinks(const std::string& text,const LinkHandler& links,const boost::algorithm::boyer_moore_horspool< std::string::const_iterator > &searcher)

// {

//     std::string texthtml = text;

//     boost::container::flat_set< std::string > linkids;

//     auto it = searcher(text.begin(),text.end());

//     while(it != text.end())

//     {

//         it = std::next(it,8);

//         auto end = std::find_if_not(it,text.end(),[](const char& c){return std::isdigit(c);});
//         if(it != end)

//            linkids.insert(std::string(it,end));

//         it = searcher(end,text.end());

//     }

//     for(auto& id: linkids)

//     {

//         auto link = links.getLink(std::stoi(id));

//         boost::algorithm::replace_all(texthtml,"[linkid:"+id+"]",link.empty()?"/":link);

//     }

//     return texthtml;

// }