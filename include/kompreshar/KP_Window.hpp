#ifndef KP_WINDOW_HPP
#define KP_WINDOW_HPP

#include <gtkmm.h>

#include <kompreshar/KP_Compressor.hpp>

class KP_Window : public Gtk::Window {
private:
  Gtk::Box m_main_box{Gtk::ORIENTATION_VERTICAL, 12};
  Gtk::Box m_control_box{Gtk::ORIENTATION_HORIZONTAL, 6};
  Gtk::HeaderBar m_header_bar;

  Gtk::FileChooserButton m_btn_filepicker;
  Gtk::Button m_btn_compress;
  Gtk::Button m_btn_decompress;

  KP_Compressor m_compressor;

  void handle_sig_compress();
  void handle_sig_decompress();

public:
  KP_Window();
  ~KP_Window();
};

#endif // KP_WINDOW_HPP
