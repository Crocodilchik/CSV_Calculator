#include "Includer.h"

int main(int argc, char *argv[]) {
    
    if (argc > 2) cout << "Incorrect arguments num" << endl;
    else
    {

        try
        {
            string filename(argv[1]);

            try
            {
                CalculateCSV calc_table(filename);
                calc_table.print_result();

            }
            catch (exception e) { cout << e.what() << endl; }

        }
        catch(...) { cout << "Incorrect string creating" << endl; }

        return 0;

    }
}