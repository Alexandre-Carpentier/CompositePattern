#include "equipment.h"
#include <string>
#include <memory >

void Client(equipment::Measurement* measurement) {

	//std::vector <MEASUREMENT> results;
	
	auto results = measurement->GetValue();
	
	std::cout << "Output instruments read: " << std::endl;
	for (auto i = results.begin(); i != results.end(); ++i)
	{
		std::cout << i->MeasurementName <<std::endl;
		std::cout << i->value << std::endl;
	}
		
}

int main(void)
{

	equipment::Composite* tree = new(equipment::Composite);
	equipment::Composite* node = new(equipment::Composite);

	equipment::Oscope* oscope1 = new(equipment::Oscope);
	equipment::Oscope* oscope2 = new(equipment::Oscope);
	equipment::Multimeter* multimeter1 = new(equipment::Multimeter);
	equipment::Multimeter* multimeter2 = new(equipment::Multimeter);
	equipment::Multimeter* multimeter3 = new(equipment::Multimeter);
	equipment::Multimeter* multimeter4 = new(equipment::Multimeter);

	node->add(oscope1);
	node->add(oscope2);

	tree->add(node);
	tree->add(multimeter1);
	tree->add(multimeter2);
	tree->add(multimeter3);
	tree->add(multimeter4);

	Client(tree);

	delete multimeter4;
	delete multimeter3;
	delete multimeter2;
	delete multimeter1;
	delete oscope2;
	delete oscope1;

	delete node;
	delete tree;

	return EXIT_SUCCESS;
}