# game backbone logging functions


function(gamebackbone_message msg)
	message("[GameBackbone] ${msg}")
endfunction()

function(gamebackbone_warning msg)
	message(WARNING "[GameBackbone] ${msg}")
endfunction()

function(gamebackbone_fatal_error msg)
	message(FATAL_ERROR "[GameBackbone] ${msg}")
endfunction()