#pragma once

static const std::string partComment = "//";
static const std::string partBlockStart = "{";
static const std::string partBlockEnd = "}";


std::string NextAfterNewLine(std::stringstream& ss, std::string& nextElement);
std::string SkipLine(std::stringstream& ss);