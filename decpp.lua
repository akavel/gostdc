-- Remove C preprocessor constructions not understood by Go language's C compiler

local getc
local unputc
local puts


-- FIXME: handle CR, CRLF, LF
function linecomment()
	puts '//'
	while true do
		local c = getc()
		puts(c)
		if c=='\n' then
			return
		end
	end
end

function blockcomment()
	puts '/*'
	while true do
		local c = getc()
		puts(c)
		if c=='*' then
			c = getc()
			if c=='/' then
				puts(c)
				return
			end
			unputc(c)
		end
	end
end

function handle_esc(c)
	if c=='\\' then
		puts(getc())
		return true
	end
	return false
end

function cstring(delim)
	puts(delim)
	while true do
		local c = getc()
		puts(c)
		if not handle_esc(c) then
			if c==delim then
				return
			end
		end
	end
end

function directive()
	-- TODO: skip whitespace after '#'
	-- TODO: read directive
	-- TODO: for '#if', read, parse and evaluate further condition
	-- TODO: based on evaluation, decide whether to enable or disable block
	-- TODO: read until '#else' or '#endif', printing contents like normally, only commented-out if needed
	while true do
		error "NYI"
	end
end

function newline()
	while true do
		local c = getc()
		if c==' ' or c=='\t' then
			puts(c)
		elseif c=='#' then
			directive()
		else
			unputc(c)
			return
		end
	end
end

function preprocess()
	local result = {}
	puts = function(s)
		result[#result+1] = s
	end

	newline()
	while true do
		local c = getc()
		if c==nil then
			break
		end

		if c=='/' then  -- maybe some comment
			local c2 = getc()
			if c2=='/' then
				linecomment()
			elseif c2=='*' then
				blockcomment()
			else
				puts(c)
				unputc(c2)
			end
		elseif c=='"' then  -- a string
			cstring(c)
		elseif c=="'" then  -- a char const
			cstring(c)
		elseif c=='\n' then
			puts(c)
			newline()
		else
			puts(c)
		end
	end

	return table.concat(result, '')
end

function main()
	if #arg<1 then
		print "USAGE: lua decpp.lua FILE.c"
		os.exit(1)
	end

	-- TODO: read list of #defined directives (and values) from commandline

	local f = assert(io.open(arg[1]))
	local unputbuf
	getc = function()
		if unputbuf then
			local c = unputbuf
			unputbuf = nil
			return c
		end
		return f:read(1)
	end
	unputc = function(c)
		assert(#c==1)
		assert(unputbuf==nil)
		unputbuf = c
	end

	local result = preprocess(f)
	f:close()

	io.stdout:write(result)
end

main()
