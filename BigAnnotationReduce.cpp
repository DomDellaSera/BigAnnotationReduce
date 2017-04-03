

#define NOMINMAX

#include <seqan/seq_io.h>
#include <string>

#include <iostream>

#include <fstream>


using namespace std;
using namespace seqan;

String<unsigned> counters;
StringSet<CharString> seqNames;
NameStoreCache<StringSet<CharString>> cache(seqNames);
std::string helpSmall = "annotationReduce.exe <input.gff3> <output.gff3>";

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << helpSmall << std::endl;
		return 1;
	}

	if (argc == 2)
	{
	std::cout << helpSmall << std::endl;
	}


	//std::cout << paath <<endl;
	//Sleep(5000)
	//string path = "c://Users/DDell/Documents/Programming/Bioinformatics/proteome_analysis_c_elegans/bigdata/b_malayi_8/";
	string annotation_File = ".\\";
	annotation_File += argv[1];
	std::cout << annotation_File;
	CharString file = annotation_File;
	string outputFile = ".\\";
	outputFile += argv[2];
	//string outputFile = "tandem.gff3";
	//string fileout = "c://Users/DDell/Documents/Programming/Bioinformatics/proteome_analysis_c_elegans/bigdata/b_malayi_8/metadata.txt";
	GffFileIn gffIn;
	//ofstream gffOut(fileout);


	if (!open(gffIn, toCString(file)))
	{
		std::cerr << "ERROR: Could not open Input File!" << std::endl;
		Sleep(5000);
		return 1;
	}



	GffRecord record;

	CharString elegans_out = outputFile;
	GffFileOut elegansOut;
	if (!open(elegansOut, toCString(elegans_out)))
	{
		std::cerr << "ERROR: Could not open File!" << std::endl;

		return 1;
	}


	try
	{
		while (!atEnd(gffIn))
		{
			readRecord(record, gffIn);
			unsigned rID = nameToId(cache, record.source); //Commenting out so we can read single records
			assignValueById(counters, rID, getValueById(counters, rID) + 1);
			if (record.source == "tandem")


			writeRecord(elegansOut, record);
			//unsigned rID = nameToId(cache, record.tagNames);
				//assignValueById(counters, rID, getValueById(counters, rID) + 1);
			//}
				//Resize counters if necessary and increment counter.


			//std::cout << seqNames[rID];


		}
	}



	catch (Exception const & e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		Sleep(5000);
		return 1;
	}




	std::cout << "RECORDS ON CONTIGS\n";
	for (unsigned i = 0; i < length(seqNames); i++)
	{
		if (counters[i] != 0u)
		{
			std::cout << seqNames[i] << '\t' << counters[i] << '\n';


		}
	}


	return 0;
}
