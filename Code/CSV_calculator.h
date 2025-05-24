#pragma once

#include "Includer.h"

using namespace std;

class CalculateCSV
{
private:

	CSVTable orig_table;
	CSVTable result_table;
	vector<vector<CellInfo>> temp_table_v;
	vector<vector<string>> final_table_v;

	void fillfinaltable_withint()
	{

		this->final_table_v.resize(this->temp_table_v.size());

		for (int i = 0; i < this->final_table_v.size(); i++)
		{

			this->final_table_v[i].resize(this->temp_table_v[i].size());

			for (int j = 0; j < this->final_table_v[i].size(); j++) 
				if (this->temp_table_v[i][j].cell_type == 2) 
					this->final_table_v[i][j] = this->temp_table_v[i][j].cell_value;

		}

	}

	int calc_operation(int a, int b, char oper)
	{

		switch (oper)
		{

		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0) throw exception("Division by zero");
			else return a / b;

		default:
			throw exception("Unrecognized operation");
			
		}

	}

	bool isnum(const char c)
	{

		switch (c)
		{

		case '0': return true;
		case '1': return true;
		case '2': return true;
		case '3': return true;
		case '4': return true;
		case '5': return true;
		case '6': return true;
		case '7': return true;
		case '8': return true;
		case '9': return true;

		default:  return false;

		}

	}

	template <typename T>
	bool is_findValue(const std::vector<T>& data, T value)
	{
		auto result{ std::find(begin(data), end(data), value) };

		if (result == end(data))
			return false;
		else
			return true;
	}

	string calc_expression(string expr, vector<pair<string, string>> enteranses)
	{

		pair<string, string> first_operand = {"", ""};
		pair<string, string> second_operand = { "", "" };
		char operation;

		int index = 1;

		while (!this->isnum(expr[index]))
		{

			first_operand.first += expr[index];
			index++;

		}

		while (this->isnum(expr[index]))
		{

			first_operand.second += expr[index];
			index++;

		}

		if (index >= expr.size())
		{

			int col_1 = this->orig_table.getcolindex(first_operand.first);
			int row_1 = this->orig_table.getrowindex(first_operand.second);
			int oper1;

			if (this->temp_table_v[row_1][col_1].cell_type == 1)
			{

				vector<pair<string, string>> ent1(enteranses);
				ent1.push_back(first_operand);
				oper1 = atoi(this->calc_expression(this->temp_table_v[row_1][col_1].cell_value, ent1).c_str());

			}
			else if (this->temp_table_v[row_1][col_1].cell_type == 2)
			{

				oper1 = atoi(this->temp_table_v[row_1][col_1].cell_value.c_str());

			}
			else throw  exception("Undefined cell type");

			return to_string(oper1);

		}

		operation = expr[index];
		index++;

		while (!this->isnum(expr[index]))
		{

			second_operand.first += expr[index];
			index++;

		}

		while (this->isnum(expr[index]))
		{

			second_operand.second += expr[index];
			index++;

		}

		if(this->is_findValue(enteranses, first_operand)) throw exception("Unbreakable recursion");
		if (this->is_findValue(enteranses, second_operand)) throw exception("Unbreakable recursion");

		int oper1, oper2;

		if (first_operand.first == "")
		{

			oper1 = atoi(first_operand.second.c_str());

		}
		else
		{

			int col_1 = this->orig_table.getcolindex(first_operand.first);
			int row_1 = this->orig_table.getrowindex(first_operand.second);

			if (this->temp_table_v[row_1][col_1].cell_type == 1)
			{

				vector<pair<string, string>> ent1(enteranses);
				ent1.push_back(first_operand);
				oper1 = atoi(this->calc_expression(this->temp_table_v[row_1][col_1].cell_value, ent1).c_str());

			}
			else if (this->temp_table_v[row_1][col_1].cell_type == 2)
			{

				oper1 = atoi(this->temp_table_v[row_1][col_1].cell_value.c_str());

			}
			else throw  exception("Undefined cell type");

		}

		if (second_operand.first == "")
		{

			oper2 = atoi(second_operand.second.c_str());

		}
		else
		{
			int col_2 = this->orig_table.getcolindex(second_operand.first);
			int row_2 = this->orig_table.getrowindex(second_operand.second);

			if (this->temp_table_v[row_2][col_2].cell_type == 1)
			{

				vector<pair<string, string>> ent2(enteranses);
				ent2.push_back(second_operand);
				oper2 = atoi(this->calc_expression(this->temp_table_v[row_2][col_2].cell_value, ent2).c_str());

			}
			else if (this->temp_table_v[row_2][col_2].cell_type == 2)
			{

				oper2 = atoi(this->temp_table_v[row_2][col_2].cell_value.c_str());

			}
			else throw exception("Undefined cell type");

		}

		return to_string(this->calc_operation(oper1, oper2, operation));


	}

	void fillfinaltable_withexpr()
	{

		vector<pair<string, string>> enteranse;

		for (int i = 0; i < this->final_table_v.size(); i++)
			for (int j = 0; j < this->final_table_v[i].size(); j++)
				if (this->temp_table_v[i][j].cell_type == 1)
					this->final_table_v[i][j] = this->calc_expression(this->temp_table_v[i][j].cell_value, enteranse);

	}

public:

	CalculateCSV(const std::string& filename): orig_table{ CSVTable(filename) }, result_table{ orig_table }
	{

		this->temp_table_v = this->orig_table.gettableonly();
		this->fillfinaltable_withint();
		this->fillfinaltable_withexpr();

		this->result_table.replacetable(this->final_table_v);

	}

	void print_orig()
	{

		this->orig_table.printtable();

	}

	void print_result()
	{

		this->result_table.printtable();

	}

};