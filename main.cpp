#include "Application.hpp"
#include "AllegroException.hpp"
#include "Actor.hpp"
#include "Application.hpp"
#include "ResourceNotLoaded.hpp"

int main(int argc, char** argv) {
	{
		Application app;
		try {
			app.init(argc, argv);
			app.loop();
		}
		catch (AllegroException &e) {
			std::cout << e.what() << std::endl;
			system("pause");
		}
		catch (ResourceNotLoaded &e) {
			std::cerr << e.what() << std::endl;
			system("pause");

		}
	}

	return 0;
}



