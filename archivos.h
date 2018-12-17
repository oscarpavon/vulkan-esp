#ifndef archivos_h
#define archivos_h
#include <fstream>
#include <vector>

static std::vector<char> leer_archivo(const std::string & nombre_de_archivo){
        std::ifstream archivo(nombre_de_archivo, std::ios::ate | std::ios::binary);

        if(!archivo.is_open()){
            throw std::runtime_error("no se cargo el archivo");
        }

        size_t tamanyo = (size_t) archivo.tellg();
        std::vector<char> bufer(tamanyo);
        archivo.seekg(0);
        archivo.read(bufer.data(), tamanyo);
        archivo.close();

        return bufer;
    }




#endif