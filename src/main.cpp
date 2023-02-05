#include <gempyre.h>
#include <gempyre_utils.h>
#include <gempyre_client.h>

#include "hexview_resource.h"

#include <iostream>
#include <iomanip>

using Bytes = std::vector<unsigned char>;

constexpr unsigned MaxBytes = 0xFFFF + 1;
constexpr unsigned BytesWidth(const unsigned value) {
    return value / 0xF == 0 ? 0 : BytesWidth(value / 0xF) + 1;
}

std::string toAscii(const Bytes& bytes) {
    auto pos = 0;
    std::string out;
    for(const auto b : bytes) {
        if(pos == 16) {
            out += "<br>";
            pos = 0;
        }
        ++pos;
        switch (b) {
        case '<': out += "&lt;"; break;
        case '>': out += "&gt;"; break;
        case '&': out += "&amp;"; break;
        case '"': out += "&quot;"; break;
        default:
            if(b >= 0x20 && b < 0x7F)
                out +=  static_cast<char>(b);
           else
                out += '.';
        }
    }
    return  out;
}

std::string toBytes(const Bytes& bytes) {
    auto pos = 0;
    std::string out;
    const std::string hex{"0123456789ABCDEF"};
    for(const auto b : bytes) {
        if(pos == 16) {
            out += "<br>";
            pos = 0;
        }
        ++pos;
        out += hex[b >> 4];
        out += hex[b & 0xF];
        out += ' ';
    }
    return  out;
}

std::string toOffset(const Bytes& bytes) {
    auto offset = 0U;
    std::stringstream stream;
    for(; offset < bytes.size(); offset += 16) {
        stream << std::uppercase << std::setfill('0') << std::setw (BytesWidth(MaxBytes)) << std::hex << offset << "<br>";
    }
    return stream.str();
}

int main(int argc, char** argv)  {
    Gempyre::set_debug();
  //  GempyreUtils::FileLogWriter lw("hexlog.txt");
  //  GempyreUtils::setLogWriter(&lw);
    Gempyre::Ui ui(Hexview_resourceh, "hexview.html");

    const auto plist = GempyreUtils::parse_args(argc, argv, {});
                          
    Gempyre::Element fileDialog(ui, "openfile");
    std::string filename;
    fileDialog.subscribe("click", [&ui, &filename](const Gempyre::Event&) {
        const auto out = Gempyre::Dialog::open_file_dialog("Pick a file");

        if(out.has_value()) {
                filename = std::any_cast<std::string>(*out);
                Gempyre::Element(ui, "filename").set_html(filename);
                const auto content = GempyreUtils::slurp<unsigned char>(filename, MaxBytes);
                Gempyre::Element ascii(ui, "ascii-field");
                ascii.set_html(toAscii(content));
                Gempyre::Element bytes(ui, "bytes-field");
                bytes.set_html(toBytes(content));
                Gempyre::Element offset(ui, "offset-field");
                offset.set_html(toOffset(content));
                if(MaxBytes < GempyreUtils::file_size(filename)) {
                    Gempyre::Element(ui, "file-cut").set_attribute("style", "display:block");
                } else {
                    Gempyre::Element(ui, "file-cut").set_attribute("style", "display:none");
                }
         } else {
            Gempyre::Element(ui, "filename").set_html("");
        }
      });
   Gempyre::Element(ui, "file-cut").set_attribute("style", "display:none");
   ui.run();
   return 0;
}
