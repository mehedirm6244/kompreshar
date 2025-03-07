/**
 * This file is from Kompreshar - a lossless text compression tool.
 * Copyright (C) 2025 Mehedi Rahman Mahi
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kompreshar/KP_Window.hpp>

#include <iostream>

KP_Window::KP_Window()
  : m_btn_filepicker("Select a file", Gtk::FILE_CHOOSER_ACTION_OPEN),
  m_btn_compress("Compress"),
  m_btn_decompress("Decompress") {
  // Set up window properties
  set_title("Kompreshar");
  set_border_width(12);
  set_default_size(350, 0);
  set_resizable(false);

  // Set up the header bar
  m_header_bar.set_title("Kompreshar");
  m_header_bar.set_subtitle("Text compressor and decompressor");
  m_header_bar.set_show_close_button(true);
  set_titlebar(m_header_bar);

  // Set up filter for the file picker
  auto filter = Gtk::FileFilter::create();
  filter->set_name("Text Files");
  filter->add_pattern("*.txt");
  filter->add_pattern("*.kpc");
  m_btn_filepicker.add_filter(filter);

  // Style the compress button as suggested action, if your GTK theme supports it
  m_btn_compress.get_style_context()->add_class("suggested-action");

  // Populate control box (containing compress/decompress button)
  m_control_box.pack_end(m_btn_compress, Gtk::PACK_SHRINK);
  m_control_box.pack_end(m_btn_decompress, Gtk::PACK_SHRINK);

  // Add widgets to the main box
  m_main_box.pack_start(m_btn_filepicker, Gtk::PACK_SHRINK);
  m_main_box.pack_start(m_control_box, Gtk::PACK_EXPAND_WIDGET);

  // Connect signal handlers
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
    bool status = m_compressor.compress_file(filename);
    show_message(status ? "File compressed successfully" : "Something went wrong",
      status ? Gtk::MESSAGE_INFO : Gtk::MESSAGE_ERROR);
  }
}

void KP_Window::handle_sig_decompress() {
  std::string filename = m_btn_filepicker.get_filename();
  if (!filename.empty()) {
    // Check if the file has the correct extension ('.kpc')
    if (filename.rfind(".kpc") != filename.length() - 4) {
      show_message("Selected file is not a \'.kpc\' file", Gtk::MESSAGE_ERROR);
      return;
    }

    std::cout << "Decompressing file :" << filename << std::endl;
    bool status = m_compressor.decompress_file(filename);
    show_message(status ? "File decompressed successfully" : "Something went wrong",
      status ? Gtk::MESSAGE_INFO : Gtk::MESSAGE_ERROR);
  }
}

void KP_Window::show_message(const std::string& message,
  Gtk::MessageType message_type) {
  Gtk::MessageDialog dialog(*this, message, false, message_type, Gtk::BUTTONS_OK);
  dialog.run();
}
