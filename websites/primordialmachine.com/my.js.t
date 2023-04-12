// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

@(>"./my/my-memory.js.template")

/**
 * @@brief The "my.toc" library.
 * @@detail Ensures the table of contents is expand in accordance with the page visited by the user.
 */
$(window).on('load', function() {
  $.my = $.my || {};

  $.my.toc = $.my.toc || {};

  var state = {
    collapsed : {
      id : 1,
      cls : 'my-toggle-collapsed',
      ico : 'fa-caret-right'
    },
    expanded : {
      id : 2,
      cls : 'my-toggle-expanded',
      ico : 'fa-caret-down'
    }
  };

  // Toggle the specified target adjusting the icon of the target.
  var toggle = function($target, $icon)
  {
    var sid = $target.hasClass(state.collapsed.cls) ? state.collapsed.id : ($target.hasClass(state.expanded.cls) ? state.expanded.id : undefined);
    switch (sid)
    {
      case state.collapsed.id:
      {
        $icon.removeClass(state.collapsed.ico);
        $icon.addClass(state.expanded.ico);
        $target.removeClass(state.collapsed.cls);
        $target.addClass(state.expanded.cls);
      } break;
      case state.expanded.id:
      {
        $icon.removeClass(state.expanded.ico);
        $icon.addClass(state.collapsed.ico);
        $target.removeClass(state.expanded.cls);
        $target.addClass(state.collapsed.cls);
      } break;
      default:
      {
        console.warn('invalid state id');
      } break;
    };
  };

  var onReady = function()
  {
    // (1) Register for the "onclick" event on "togglers".
    $('.toc a.nav-link.my-toggle').on
    (
      'click',
      function(e)
      {
        e.preventDefault();
        var $target = $(this).parent().next(); // Get target.
        var $icon = $(this).children().next().children(); // Get icon.
        toggle($target, $icon);
      }
    );
    // (2) Expand recursively the table of contents to the link of the currently visited page.

    var configureTree = function($link) {
      if ($link.length > 0)
      {
        var $targets = $link.parent().parent();
        var configureTree = function($target) {
          var $icon = $target.prev().children(':first').children().next().children();
          toggle($target, $icon);
          $target = $target.parent().closest('div.my-toggle-collapsible');
          if ($target.length == 1) {
            configureTree($target);
          }
        };
        $targets.each(function() {
          configureTree($(this));
        });
      } else {
        console.warn('invalid table of contents');
      }
    };
    
    var delay = 10;
    var duration = undefined;
    var easing = undefined;
    
    var defaultDelay = 100;
    var defaultDuration = 400; // https://api.jquery.com/animate/
    var defaultEasing = 'swing'; // https://api.jquery.com/animate/
    
    /** 
     * Scroll ancestor scrollable element such that a a descendant element is visible.
     * @@param a The ancestor element.
     * @@param d The descendant element.
     */
    var configureScrollBar = function(nav, d) {
      var $nav = jQuery(nav);
      var $nav_top = $nav.offset().top;
      var $nav_top_2 = $nav[0].offsetTop;
      var $nav_bottom = $nav_top + $nav.height();
      
      var $d = jQuery(d);
      var $d_top = $d.offset().top;
      var $d_top_2 = $d[0].offsetTop;
      var $d_bottom = $d_top + $d.height();

      if ($d_top > $nav_top && $d_bottom < $nav_bottom) {
          // in view so don't do anything
          return;
      }
      var new_scroll_top;
      var old_scroll_top = $nav.scrollTop();
      if ($d_top < $nav_top) {
          new_scroll_top = $nav.scrollTop() - $nav_top + $d_top;
      } else {
          new_scroll_top = $d_top - $nav_top + old_scroll_top;
      }
      $nav.animate({scrollTop : new_scroll_top},
                   duration === undefined ? defaultDuration : duration,
                   easing === undefined ? defaultEasing : easing);
      return $nav;
    };
    
    var href = window.location.pathname + window.location.hash;      // Use pathname if we are using root relative links.
    var $link = $("a[href='" + href + "'][class='nav-link']:eq(1)"); // TODO: The way how bootstrap works, there are multiple links?
    if ($link.length > 0) {
      $.when(configureTree($link)).done(function() {
        $nav = $link;
        while (!$nav.is('nav')) {
          $nav = $nav.parent();
        }
        setTimeout(function() {
          configureScrollBar($nav, $link);
        }, delay === undefined ? defaultDelay : delay);
      }());
      }
  };

  onReady();
});
