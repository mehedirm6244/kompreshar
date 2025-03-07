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

#ifndef KP_WINDOW_HPP
#define KP_WINDOW_HPP

#include <gtkmm.h>

#include <kompreshar/KP_Compressor.hpp>

class KP_Window : public Gtk::Window {
private:
  // Main container for organizing widgets.
  Gtk::Box m_main_box{Gtk::ORIENTATION_VERTICAL, 12};

  // Container for organizing control buttons (compress/decompress).
  Gtk::Box m_control_box{Gtk::ORIENTATION_HORIZONTAL, 6};

  // Header bar for the window.
  Gtk::HeaderBar m_header_bar;

  // Button for selecting a file to compress or decompress.
  Gtk::FileChooserButton m_btn_filepicker;

  // Button to trigger the compression process.
  Gtk::Button m_btn_compress;

  // Button to trigger the decompression process.
  Gtk::Button m_btn_decompress;

  // Instance of KP_Compressor to handle compression and decompression logic.
  KP_Compressor m_compressor;

  /**
   * Show popup message/dialog using Gtk::MessageDialog
   * 
   * @param message: The message to display.
   * @param message_type: The type of message (e.g. Gtk::MESSAGE_ERROR).
   */
  void show_message(const std::string& message, Gtk::MessageType message_type);

  // Handle the signal when the compress button is clicked.
  void handle_sig_compress();

  // Handle the signal when the decompress button is clicked.
  void handle_sig_decompress();

public:
  KP_Window();
  ~KP_Window();
};

#endif // KP_WINDOW_HPP
