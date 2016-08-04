

j$( document ).ready(function() {
    
    var fieldNameElement = document.getElementById("myId");
    fieldNameElement.innerHTML = "0";
    
    j$("#imgId").mousemove(function(e){
       var wrapper = j$(this).parent();
       var parentOffset = wrapper.offset(); 
       var relX = e.pageX - parentOffset.left + wrapper.scrollLeft();
       var relY = e.pageY - parentOffset.top + wrapper.scrollTop();

       var scale = 2;

       var imgWidth = 608*scale;
       var imgHeight = 576*scale;
       
       var iconWidth = (16*scale);
       var iconsPerRow = Math.floor(imgWidth/iconWidth);

       fieldNameElement.innerHTML = Math.floor(relX/iconWidth) + Math.floor(relY/iconWidth)*iconsPerRow;
        
    });
});


