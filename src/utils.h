#include <string>

std::string space(std::string text, int espacio){
    std::string out;
    if(espacio>0){
        for(int i=0; i<espacio; i++){
            if(i<text.size()){
                out.push_back(text.c_str()[i]);
            } else {
                out.push_back(' ');
            }
        }
    } else {
        for(int i=espacio; i<0; i++){
            if(i+text.size()>0){
                out.push_back(text.c_str()[i+text.size()]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}