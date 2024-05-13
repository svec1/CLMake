#ifndef VAR__H_
#define VAR__H_

#include "../../../bin/include.h"
#include "target_ex.h"

namespace variable
{
    template <typename T>
    class variable
    {
    public:
        variable()
        {
            VAR_INT = new T[1];
            SIZE_VAR_INT = 1;
        }
        void add()
        {
            T *newArr = new T[SIZE_VAR_INT + 1];
            for (uint64_t i = 0; i < SIZE_VAR_INT; ++i)
            {
                newArr[i] = VAR_INT[i];
            }
            ++SIZE_VAR_INT;
            delete[] VAR_INT;
            VAR_INT = newArr;
        }
        void del()
        {
            T *newArr = new T[SIZE_VAR_INT - 1];
            for (uint64_t i = 0; i < SIZE_VAR_INT - 1; ++i)
            {
                newArr[i] = VAR_INT[i];
            }
            --SIZE_VAR_INT;
            delete[] VAR_INT;
            VAR_INT = newArr;
        }
        void clear()
        {
            T *newArr = new T[1];
            delete[] VAR_INT;
            VAR_INT = newArr;
            SIZE_VAR_INT = 1;
            NAME_VAR_INT.clear();
        }
        uint64_t size()
        {
            return SIZE_VAR_INT;
        }
        T &operator[](uint64_t index)
        {
            if (index > SIZE_VAR_INT || index < 0)
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Index specified Variable: " + toString(index));
            }
            return VAR_INT[index];
        }

        std::string get_name(uint64_t index)
        {
            if (index > SIZE_VAR_INT || index < 0)
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Index specified Variable: " + toString(index));
            }
            return NAME_VAR_INT[index];
        }

        void createVar(std::string name, T value)
        {
#ifdef DEBUG__
            std::cout << "was created variable " << name << std::endl;
#endif
            NAME_VAR_INT.push_back(name);
            VAR_INT[SIZE_VAR_INT - 1] = value;
            add();
        }

        void redataVar(uint64_t index, T value)
        {
#ifdef DEBUG__
            std::cout << NAME_VAR_INT[index] << " - redata is value" << std::endl;
#endif
            if (index > SIZE_VAR_INT || index < 0)
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Index specified Variable: " + toString(index));
            }
            VAR_INT[index] = value;
        }

        uint64_t find_(std::string name)
        {
            for (uint64_t i = 0; i < NAME_VAR_INT.size(); ++i)
            {
                if (name == NAME_VAR_INT[i])
                {
                    return i;
                }
            }
            return -1;
        }

        ~variable()
        {
            delete[] VAR_INT;
            VAR_INT = nullptr;
            SIZE_VAR_INT = 0;
        }

    private:
        T *VAR_INT;
        std::vector<std::string> NAME_VAR_INT;
        uint64_t SIZE_VAR_INT;
    };

    template <typename T>
    class VariableVector
    {
    public:
        VariableVector()
        {
            vec = new std::vector<T>[1];
            SIZE_VAR_VEC = 1;
        }

        void add()
        {
            std::vector<T> *newArr = new std::vector<T>[SIZE_VAR_VEC + 1];
            for (uint64_t i = 0; i < SIZE_VAR_VEC; ++i)
            {
                newArr[i] = vec[i];
            }
            ++SIZE_VAR_VEC;
            delete[] vec;
            vec = newArr;
        }
        void del()
        {
            std::vector<T> *newArr = new std::vector<T>[SIZE_VAR_VEC - 1];
            for (uint64_t i = 0; i < SIZE_VAR_VEC - 1; ++i)
            {
                newArr[i] = vec[i];
            }
            --SIZE_VAR_VEC;
            delete[] vec;
            vec = newArr;
        }
        void clear()
        {
            std::vector<T> *newArr = new std::vector<T>[1];
            delete[] vec;
            vec = newArr;
            SIZE_VAR_VEC = 1;
            NAME_VAR_VEC.clear();
        }
        uint64_t size()
        {
            return SIZE_VAR_VEC;
        }
        std::vector<T> &operator[](uint64_t index)
        {
            if (index > SIZE_VAR_VEC || index < 0)
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Index specified Variable: " + toString(index));
            }
            return vec[index];
        }

        std::string get_name(uint64_t index)
        {
            if (index > SIZE_VAR_VEC || index < 0)
            {
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Index specified Variable: " + toString(index));
            }
            return NAME_VAR_VEC[index];
        }

        void createVar(std::string name, std::vector<T> value)
        {
#ifdef DEBUG__
            std::cout << "was created array variable " << name << std::endl;
            std::cout << "List elements: " << std::endl;
            for (uint64_t i = 0; i < value.size(); ++i)
            {
                std::cout << value[i] << std::endl;
            }
#endif
            NAME_VAR_VEC.push_back(name);
            vec[SIZE_VAR_VEC - 1] = value;
            add();
        }

        void redataVar(uint64_t index, std::vector<T> value)
        {
            if (index > SIZE_VAR_VEC || index < 0)
                error__::ERR.callError("FATAL_ERR_VARIABLE_NF", "Index specified Variable: " + toString(index));
            vec[index] = value;
#ifdef DEBUG__
            std::cout << NAME_VAR_VEC[index] << " - redata is value " << std::endl;
            std::cout << "List elements: " << std::endl;
            for (uint64_t i = 0; i < value.size(); ++i)
            {
                std::cout << value[i] << std::endl;
            }
#endif
        }

        uint64_t find_(std::string name)
        {
            for (uint64_t i = 0; i < NAME_VAR_VEC.size(); ++i)
            {
                if (name == NAME_VAR_VEC[i])
                {
                    return i;
                }
            }
            return -1;
        }

        ~VariableVector()
        {
            delete[] vec;
            vec = nullptr;
            SIZE_VAR_VEC = 0;
        }

    private:
        std::vector<T> *vec;
        std::vector<std::string> NAME_VAR_VEC;
        uint64_t SIZE_VAR_VEC;
    };

    extern variable<double> DOUBLE_;
    extern variable<std::string> STRING_;
    extern variable</* Linker_flags, config_project */ std::pair<std::string, executable::ENUM_EXE>> TARGETS_;
    extern variable<std::pair<std::string, std::string>> STRUCT_;
    extern variable<std::pair<std::string, std::string>> FILE_PATH_;
    extern VariableVector<std::string> VEC_STRING_;
    extern VariableVector<std::string> templateGenerate;
    extern variable<std::string> AD_PARAM;
}

#endif