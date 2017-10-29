#include <thread>
#include <unistd.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "dots.h"

class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

void Dots::run() {
	std::thread t([this]() {
		std::ifstream       file("data.csv");

		CSVRow              row;
		int base = 0;
		while(file >> row)
		{
			int ts = std::stoull(row[1]);
			double lat = std::stod(row[2]);
			double lng = std::stod(row[3]);

			dots[dots.size()] = Dot{lat, lng, 0};

			if (base > 0) {
				//usleep((ts - base) / 10000);
			}

			base = ts;
		}

		/*double min_lat =  -4.647451;
		double max_lat = 7.380453;
		double min_lng = 42.857748;
		double max_lng = 50.737176;

		for (int i = 0; i < 80000; i++) {
			double lat = (double)(rand()) / RAND_MAX * (max_lat - min_lat) + min_lat;
			double lng = (double)(rand()) / RAND_MAX * (max_lng - min_lng) + min_lng;

			dots[dots.size()] = Dot{lat, lng, 0};

			if (dots.size() % 1000 == 0) {
				printf("%d items\n", dots.size());
			}
		}*/
	});

	t.detach();
}