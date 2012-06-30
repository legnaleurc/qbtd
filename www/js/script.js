$('#password2').blur( function(){
   if( $('#password').attr('value') !== $('#password2').attr('value') ){
      $('#pwd-group').addClass('error');
      $('#pwd-help').removeClass('hide');
   }else{
      $('#pwd-group').removeClass('error');
      $('#pwd-help').addClass('hide');
   }
});

