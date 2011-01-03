jQuery.fn.lumen = function(options) {
  jQuery(this).click(function() {
    var settings = jQuery.extend( {
      width: 600,
      height: 400
    },options);
    
    var lumen_contents = '<div id="lumen_wrapper"></div>';
    lumen_contents +=    '<div id="lumen_window">';
    lumen_contents +=    '<div class="title">'+jQuery(this).attr('title')+'</div>';
    lumen_contents +=    '<div class="close"><a href="#">close</a></div>';
    lumen_contents +=    '<div class="contents"><img src="'+jQuery(this).attr('href')+'" width="'+settings.width+'" height="'+settings.height+'" /></div>';
    lumen_contents +=    '</div>';
    
    jQuery('body').append(lumen_contents);
    var Yoffset = jQuery(window).scrollTop();
    var Xoffset = jQuery('#lumen_window').offset();
    jQuery('#lumen_window').css('width', settings.width + 'px');
    jQuery('#lumen_window .title').css('width', settings.width + 'px');
    jQuery('#lumen_window').css('height', settings.height + 20 + 'px');
    jQuery('#lumen_window').css('margin-top', Yoffset + parseInt((jQuery(document).height() - 50 - jQuery('#lumen_window').height()) / 2) + 'px');
    jQuery('#lumen_window').css('margin-left', Xoffset.left + parseInt((jQuery(document).width() - jQuery('#lumen_window').width()) / 2) + 'px');
    jQuery('#lumen_wrapper').css('height', jQuery(document).height() + 50 + 'px');
    jQuery('#lumen_wrapper').css('width', jQuery(window).width() + 50 + 'px');
    jQuery('body').css('overflow', 'hidden');
    jQuery('#lumen_wrapper').click(function() { hide_lumen(); });
    
    jQuery('#lumen_window .close').click(function() {
        hide_lumen();
        return false;
    });
      
    document.onkeyup = function(e) {    
        if (e == null) { // ie
            keycode = event.keyCode;
        } else { // mozilla
            keycode = e.which;
        }
        if(keycode == 27){ // close
            hide_lumen();
        }   
    }
        
    function hide_lumen() {
      jQuery('body').css('overflow', 'auto');
      jQuery('#lumen_window').remove();
      jQuery('#lumen_wrapper').remove();
    }
    
    return false;
    
  });
}