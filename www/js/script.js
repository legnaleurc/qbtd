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

$('#email').blur( function(){
   var email = $('#email').attr('value');
   if( email == '' ){
      $('#email-group').removeClass('success');
      $('#email-group').addClass('error');
      $('#email-hint').text('email can not be empty');
      $('#email-hint').removeClass('hide');
   }else{
      $('#email-group').removeClass('error');
      $('#email-group').removeClass('success');
      $('#email-hint').addClass('hide');

      $.ajax( {
         url: 'http://zbla.us/demo/qbtd/www/index.php/user/checkemail/' + encodeURIComponent(email),
         dataType: 'json',
         error: function(){ console.log('error'); },
         success: function(response){
            console.log('success');
            console.log('server response' + response);
            emailCheck( response.found );
         }
      });
   }
});

function emailCheck( found ){
   console.log('found = ' + found);
   if( found == false ){
      console.log('email not found');
      $('#email-group').removeClass('error');
      $('#email-group').addClass('success');
      $('#email-hint').text('OK!');
      $('#email-hint').removeClass('hide');
   }else if( found == true ){
      console.log('email found');
      $('#email-group').removeClass('success');
      $('#email-group').addClass('error');
      $('#email-hint').text('email has been used');
      $('#email-hint').removeClass('hide');
   }else{
      // Hide status
      console.log('hide message');
      $('#email-group').removeClass('error');
      $('#email-group').removeClass('success');
      $('#email-hint').addClass('hide');
   }
}
