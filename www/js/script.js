$('#password2').blur( function(){
   if( $('#password').attr('value') !== $('#password2').attr('value') ){
      $('#pwd-group').addClass('error');
      $('#pwd-help').removeClass('hide');
   }else{
      $('#pwd-group').removeClass('error');
      $('#pwd-help').addClass('hide');
   }
});


$('#username').blur( function(){
   var username = $('#username').attr('value');
   if( username == '' ){
      $('#username-group').removeClass('success');
      $('#username-group').addClass('error');
      $('#username-hint').text('Username can not be empty');
      $('#username-hint').removeClass('hide');
   }else{
      $('#username-group').removeClass('error');
      $('#username-group').removeClass('success');
      $('#username-hint').addClass('hide');

      $.ajax( {
         url: 'http://zbla.us/demo/qbtd/www/index.php/user/checkUsername/' + username,
         dataType: 'json',
         error: function(){ console.log('error'); },
         success: function(response){
            console.log('success');
            console.log('server response' + response);
            usernameCheck( response.found );
         }
      });
   }
});

function usernameCheck( found ){
   console.log('found = ' + found);
   if( found == false ){
      console.log('username not found');
      $('#username-group').removeClass('error');
      $('#username-group').addClass('success');
      $('#username-hint').text('OK!');
      $('#username-hint').removeClass('hide');
   }else if( found == true ){
      console.log('username found');
      $('#username-group').removeClass('success');
      $('#username-group').addClass('error');
      $('#username-hint').text('Username has been used');
      $('#username-hint').removeClass('hide');
   }else{
      // Hide status
      console.log('hide message');
      $('#username-group').removeClass('error');
      $('#username-group').removeClass('success');
      $('#username-hint').addClass('hide');
   }
}
