jQuery(document).ready(function ($) {

  var smallIpop = $('.smallipop');
  if (smallIpop.length > 0) {
    smallIpop.smallipop({
      invertAnimation: true,
      preferredPosition: 'left',
      theme: 'default',
      popupOffset: 0
    });
  }
});
