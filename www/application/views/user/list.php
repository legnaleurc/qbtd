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
         <td>Ubuntu-12.04-desktop-amd128.iso.torrent</td>
         <td style="width: 200px;"> <div class="progress"> <div class="bar" style="width: 70%;"></div></div></td>
         <td style=""> 
            <a class="action-link" href="#"><i class="action-icon icon-download-alt"></i>Download</a> 
            <a class="action-link" href="#"><i class="action-icon icon-trash"></i>Delete</a>
            <a class="action-link" href="#"><i class="action-icon icon-info-sign"></i>Detail</a>
         </td>
      </tr>
      </tbody>
   </table>

<?php $this->load->view('footer');  ?>
