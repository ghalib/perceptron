#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

#include <string>
#include "featurevector.hpp"

class Document {
private:
  std::string content;
  std::string title;
  FeatureVector features;
  size_t doc_id;
public:
  Document();
  Document(const std::string&);
  Document(const std::string&, const std::string&);
  void set_features(const FeatureVector&);
  FeatureVector get_features() const;
  bool has_features() const;
  void set_doc_id(size_t id);
  size_t get_doc_id() const;
  std::string get_content() const;
  std::string get_title() const;
  bool empty() const;
};

#endif
