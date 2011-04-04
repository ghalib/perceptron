#include "document.hpp"

Document::Document() {}

Document::Document(const std::string& content_) : content(content_) {}

Document::Document(const std::string& content_,
		   const std::string& title_) : content(content_), title(title_) {}

void Document::set_features(const FeatureVector& fv) {
  features = fv;
}

const FeatureVector& Document::get_features() const {
  return features;
}

bool Document::has_features() const {
  return !(features.empty());
}

void Document::set_doc_id(size_t id) {
  doc_id = id;
}

size_t Document::get_doc_id() const {
  return doc_id;
}

std::string Document::get_content() const {
  return content;
}

std::string Document::get_title() const {
  return title;
}

bool Document::empty() const {
  return content.empty();
}
