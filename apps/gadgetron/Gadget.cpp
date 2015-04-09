#include "Gadget.h"
#include "GadgetStreamController.h"

namespace Gadgetron
{
  boost::shared_ptr<std::string> Gadget::get_string_value(const char* name, unsigned int recursive) {
    const unsigned int recursive_limit = 10;
    if (recursive > recursive_limit) {
      GDEBUG("Recursive level %d exceeds maimum limit (%d) in Gadget::get_string_value(...)\n", recursive, recursive_limit);
      return boost::shared_ptr<std::string>(new std::string(""));
    }

    std::string str_val;
    GadgetPropertyBase* p = find_property(name);
    if (using_properties_) {
      if (!p) {
	GERROR("Property %s\n", name);
	throw std::runtime_error("Attempting to access non existent property on Gadget");
      }
      str_val = std::string(p->string_value());
    } else {
      std::map<std::string,std::string>::iterator it;
      parameter_mutex_.acquire();
      it = parameters_.find(std::string(name));
      parameter_mutex_.release();
      if (it != parameters_.end()) {
	str_val = it->second;
      }
    }

    //If string contains an @ sign, we should look for this parameter on another gadget
    size_t at_pos = str_val.find('@');
    if (at_pos != std::string::npos) {
      //There was an add sign, which means look for that parameter on another gadget
      std::string parm = str_val.substr(0,at_pos);
      std::string gadget = str_val.substr(at_pos+1);
	  
      Gadget* ref_gadget = this->controller_->find_gadget(gadget.c_str());
      
      if (ref_gadget) {
	recursive++;
	return ref_gadget->get_string_value(parm.c_str(), recursive);
      }
    } else {
      return boost::shared_ptr<std::string>(new std::string(str_val));
    }

    return boost::shared_ptr<std::string>(new std::string(""));
  }
}
