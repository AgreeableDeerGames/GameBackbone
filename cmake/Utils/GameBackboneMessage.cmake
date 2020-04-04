# game backbone logging functions


function(gamebackbone_message msg)
	message("[GameBackbone] ${msg}")
endfunction()

function(gamebackbone_warning msg)
	message(WARNING "[GameBackbone] ${msg}")
endfunction()