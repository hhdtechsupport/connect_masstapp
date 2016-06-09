  /* helpers */
    // helper functions
    function toInt(myString) {
      var myInt;
      myInt = parseInt(myString.substring(0, myString.length - 2));
      return myInt;
    }

    function makeString(myInt) {
      var myString;
      myString = myInt.toString() + 'px';
      return myString;
    }

    function setHeights() {

      var sideBar = $('.region-sidebar-second.column.sidebar').css('height');

      var centerContent = $('div#content').css('height');

      var sb = toInt(sideBar);
      var cc = toInt(centerContent);

      var newHeight = (sb < cc) ? cc : sb;

      var finalConHeight = makeString(newHeight+40);

      $('.region-sidebar-second.column.sidebar').css('height',newHeight);
      $('div#content').css('height',finalConHeight);

    }
    if ($('body').hasClass('section-events2')) setHeights();