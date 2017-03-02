-- load the http module
local http = require'socket.http'
local ltn12 = require"ltn12"


function post_request(url, POST_DATA)
	local respbody = {}

	-- Requests information about a document, without downloading it.
	-- Useful, for example, if you want to display a download gauge and need
	-- to know the size of the document in advance
	r, s, c = http.request {
	  method = "POST",
	  url = url,
	  sink = ltn12.sink.table(respbody),
	  headers = {
	            ["content-type"] = "application/json",
	            ["content-length"] = tostring(#POST_DATA)
	        }
	}

	-- get body as string by concatenating table filled by sink
	respbody = table.concat(respbody)

	return respbody
end

function get_request(url)
	print"get_request"
	local respbody = {}

	-- Requests information about a document, without downloading it.
	-- Useful, for example, if you want to display a download gauge and need
	-- to know the size of the document in advance
	r, s, c = http.request {
	  method = "GET",
	  url = url,
	  sink = ltn12.sink.table(respbody)
	}

	-- get body as string by concatenating table filled by sink
	respbody = table.concat(respbody)

	return respbody
end
