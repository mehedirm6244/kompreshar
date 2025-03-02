#ifndef KPWINDOW_HPP
#define KPWINDOW_HPP

#include <gtkmm.h>

#include "KPCompressor.cpp"

class KPWindow : public Gtk::Window {
private:
  Gtk::Box m_main_box{Gtk::ORIENTATION_VERTICAL, 12};
  Gtk::Box m_control_box{Gtk::ORIENTATION_HORIZONTAL, 6};
  Gtk::HeaderBar m_header_bar;

  Gtk::FileChooserButton m_btn_filepicker;
  Gtk::Button m_btn_compress;
  Gtk::Button m_btn_decompress;

  KPCompressor m_compressor;

  void handle_sig_compress();
  void handle_sig_decompress();

public:
  KPWindow();
  ~KPWindow();
};

#endif // KPWINDOW_HPP
