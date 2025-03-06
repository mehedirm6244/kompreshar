#include <kompreshar/KP_Window.hpp>

#include <iostream>

KP_Window::KP_Window()
  : m_btn_filepicker("Select a file", Gtk::FILE_CHOOSER_ACTION_OPEN),
  m_btn_compress("Compress"),
  m_btn_decompress("Decompress") {
  set_title("Kompreshar");
  set_border_width(12);
  set_default_size(350, 0);
  set_resizable(false);

  m_header_bar.set_title("Kompreshar");
  m_header_bar.set_subtitle("Text compressor and decompressor");
  m_header_bar.set_show_close_button(true);
  set_titlebar(m_header_bar);

  auto filter = Gtk::FileFilter::create();
  filter->set_name("Text Files");
  filter->add_pattern("*.txt");
  filter->add_pattern("*.kpc");
  m_btn_filepicker.add_filter(filter);

  m_btn_compress.get_style_context()->add_class("suggested-action");

  m_control_box.pack_end(m_btn_compress, Gtk::PACK_SHRINK);
  m_control_box.pack_end(m_btn_decompress, Gtk::PACK_SHRINK);

  m_main_box.pack_start(m_btn_filepicker, Gtk::PACK_SHRINK);
  m_main_box.pack_start(m_control_box, Gtk::PACK_EXPAND_WIDGET);

  m_btn_compress.signal_clicked().connect(
    sigc::mem_fun(*this, &KP_Window::handle_sig_compress));
  m_btn_decompress.signal_clicked().connect(
    sigc::mem_fun(*this, &KP_Window::handle_sig_decompress));

  add(m_main_box);
  show_all_children();
}

KP_Window::~KP_Window() {
  // Nothing to clean up
}

void KP_Window::handle_sig_compress() {
  std::string filename = m_btn_filepicker.get_filename();
  if (!filename.empty()) {
    std::cout << "Compressing file :" << filename << std::endl;
    bool success = (m_compressor.compress_file(filename) == 0);
    Gtk::MessageDialog dialog(*this,
      success ? "File compressed successfully" : "Something went wrong",
      false,
      success ? Gtk::MESSAGE_INFO : Gtk::MESSAGE_ERROR,
      Gtk::BUTTONS_OK);
    dialog.run();
  }
}

void KP_Window::handle_sig_decompress() {
  std::string filename = m_btn_filepicker.get_filename();
  if (!filename.empty()) {
    if (filename.rfind(".kpc") != filename.length() - 4) {
      Gtk::MessageDialog dialog(*this, "Selected file is not a \'.kpc\' file", false,
        Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
      dialog.run();
      return;
    }

    std::cout << "Decompressing file :" << filename << std::endl;
    bool success = (m_compressor.decompress_file(filename) == 0);
    Gtk::MessageDialog dialog(*this,
      success ? "File decompressed successfully" : "Something went wrong",
      false,
      success ? Gtk::MESSAGE_INFO : Gtk::MESSAGE_ERROR,
      Gtk::BUTTONS_OK);
    dialog.run();
  }
}
