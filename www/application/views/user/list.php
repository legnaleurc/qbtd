<?php
   $this->load->view('header');  
   $this->load->view('navbar'); 
   $this->load->helper('url');  
?>

   <h2>Hello, <?php echo $user['id']; ?></h2>

   <p style="margin-top: 25px;"></p>
   
   <table class="table">
      <tbody>
         <tr>
            <td>Project Name</td>
            <td>Progress</td>
            <td>Actions</td>
         <tr>

      <tr>
         <td>johnroyer</td>
         <td> <div class="progress"> <div class="bar" style="width: 70%;"></div></div></td>
         <td style="width:250px;"> 
            <i class="icon-download-alt"></i><a href="#">Download</a> 
            <i class="icon-trash"></i><a href="#">Delete</a>
            <i class="icon-info-sign"></i><a href="#">Detail</a>
            <i class=""></i><a href="#"></a>
         </td>
      </tr>
      </tbody>
   </table>

<?php $this->load->view('footer');  ?>
