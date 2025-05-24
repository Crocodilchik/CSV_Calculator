#pragma once

#include "Includer.h"

using namespace std;

struct CellInfo
{
public:

    std::string cell_value;
    unsigned cell_type;

    CellInfo(std::string val) : cell_value{ val }
    {


        if (val[0] == '=') cell_type = 1;
        else
        {

            switch (val[0])
            {

            case '0': cell_type = 2; break;
            case '1': cell_type = 2; break;
            case '2': cell_type = 2; break;
            case '3': cell_type = 2; break;
            case '4': cell_type = 2; break;
            case '5': cell_type = 2; break;
            case '6': cell_type = 2; break;
            case '7': cell_type = 2; break;
            case '8': cell_type = 2; break;
            case '9': cell_type = 2; break;

            default:  cell_type = 0; break;

            }

        }

    }

};

class CSVTable
{
private:

	map<string, int> colls_id_to_index;
	//map<int, string> colls_index_to_id;
	map<string, int> rows_id_to_index;
	//map<int, string> rows_index_to_id;
	vector<vector<CellInfo>> table_info;

    void getcollsCSV(ifstream &file)
    {

        string line;

        try { getline(file, line); }
        catch (...)
        {

            cerr << "Error in file reading" << endl;
            return;

        }

        stringstream ss(line);
        string value;
        int index = 0;

        getline(ss, value, ',');

        while (getline(ss, value, ','))
        {

            this->colls_id_to_index[value] = index;
            //this->colls_index_to_id[index] = value;
            index++;

        }

    }

    void getrowsCSV(ifstream &file)
    {

        string line;
        int map_index = 0;
        int vector_index = 0;

        while (getline(file, line))
        {

            stringstream ss(line);
            string value;
            vector<string> row;

            getline(ss, value, ',');

            this->rows_id_to_index[value] = map_index;
            //this->rows_index_to_id[map_index] = value;
            map_index++;

            vector<CellInfo> v;
            this->table_info.push_back(v);


            while (getline(ss, value, ','))
            {

                CellInfo cellval(value);
                if (cellval.cell_type == 0) throw  exception("Undefined cell type");
                this->table_info[vector_index].push_back(cellval);

            }

            vector_index++;

        }

    }

public:

    CSVTable(const std::string& filename)
    {

        ifstream file(filename);

        if (!file.is_open())
        {

            cerr << "Error in file opening" << endl;
            return;

        }

        this->getcollsCSV(file);
        this->getrowsCSV(file);

        file.close();

    }

    CSVTable(const CSVTable &othertable)
    {

        this->colls_id_to_index = othertable.colls_id_to_index;
        this->rows_id_to_index = othertable.rows_id_to_index;
        this->table_info = othertable.table_info;

    }

    CSVTable()
    {

    }

    void printtable(int wight = 15)
    {

        cout << setw(wight) << "  ";

        for (const auto& element : this->colls_id_to_index)
        {

            cout << setw(wight) << element.first;

        }

        cout << endl;

        int index = 0;

        for (const auto& element : this->rows_id_to_index)
        {

            cout << setw(wight) << element.first;

            for (const auto& element : this->table_info[index])
            {

                cout << setw(wight) << element.cell_value;

            }

            index++;
            cout << endl;

        }

    }

    void printcelltypes(int wight = 15)
    {

        cout << setw(wight) << "  ";

        for (const auto& element : this->colls_id_to_index)
        {

            cout << setw(wight) << element.first;

        }

        cout << endl;

        int index = 0;

        for (const auto& element : this->rows_id_to_index)
        {

            cout << setw(wight) << element.first;

            for (const auto& element : this->table_info[index])
            {
                string celltype;

                switch (element.cell_type)
                {  

                case 2: celltype = "Integer"; break;
                case 1: celltype = "Expression"; break;

                default: celltype = "Undefined"; break;
                }

                cout << setw(wight) << celltype;

            }

            index++;
            cout << endl;

        }

    }

    vector<vector<CellInfo>> gettableonly()
    {

        vector<vector<CellInfo>> result(this->table_info);

        return result;

    }

    int getrowindex(string str)
    {
        if (!this->rows_id_to_index.count(str))
        {

            throw  exception("No such row id");

        }

        return this->rows_id_to_index[str];

    }

    int getcolindex(string str)
    {
        if (!this->colls_id_to_index.count(str))
        {

            throw  exception("No such col id");

        }

        return this->colls_id_to_index[str];

    }

    void replacetable(vector<vector<string>> new_table)
    {

        if (new_table.empty() || new_table[0].empty())
        {

            throw  exception("Table has an incorrect format");

        }

        if (this->rows_id_to_index.size() != new_table.size())
        {

            throw  exception("Table has an incorrect row size");

        }

        if (this->colls_id_to_index.size() != new_table[0].size())
        {

            throw  exception("Table has an incorrect col size");

        }

        for (int i = 0; i < new_table.size(); i++) {

            for (int j = 0; j < new_table[i].size(); j++) this->table_info[i][j] = CellInfo(new_table[i][j]);

        }

    }

};